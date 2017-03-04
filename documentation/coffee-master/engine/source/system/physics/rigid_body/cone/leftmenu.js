function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6399\" class=\"headerLeftMenuInActive\"><a id=\"aID6399\" href=\"#\" OnMouseOver=\"link('_dir','cone0',this)\" class=\"leftMenuLinkHeadInActive\">cone</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID918\" class=\"leftMenuInActive\"><a id=\"aID918\" href=\"#\" OnMouseOver=\"link('_class','Cone14855',this)\" class=\"leftMenuLinkInActive\">Cone</a></div>\n");
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
