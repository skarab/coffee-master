function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6405\" class=\"headerLeftMenuInActive\"><a id=\"aID6405\" href=\"#\" OnMouseOver=\"link('_dir','bounding0',this)\" class=\"leftMenuLinkHeadInActive\">bounding</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID925\" class=\"leftMenuInActive\"><a id=\"aID925\" href=\"#\" OnMouseOver=\"link('_class','Bounding42087',this)\" class=\"leftMenuLinkInActive\">Bounding</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
