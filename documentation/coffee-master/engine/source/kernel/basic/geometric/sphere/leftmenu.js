function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6280\" class=\"headerLeftMenuInActive\"><a id=\"aID6280\" href=\"#\" OnMouseOver=\"link('_dir','sphere0',this)\" class=\"leftMenuLinkHeadInActive\">sphere</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID740\" class=\"leftMenuInActive\"><a id=\"aID740\" href=\"#\" OnMouseOver=\"link('_class','Sphere39014',this)\" class=\"leftMenuLinkInActive\">Sphere</a></div>\n");
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
