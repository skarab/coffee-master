function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6396\" class=\"headerLeftMenuInActive\"><a id=\"aID6396\" href=\"#\" OnMouseOver=\"link('_dir','capsule0',this)\" class=\"leftMenuLinkHeadInActive\">capsule</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID915\" class=\"leftMenuInActive\"><a id=\"aID915\" href=\"#\" OnMouseOver=\"link('_class','Capsule14855',this)\" class=\"leftMenuLinkInActive\">Capsule</a></div>\n");
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
