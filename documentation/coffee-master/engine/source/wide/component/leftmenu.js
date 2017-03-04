function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6415\" class=\"headerLeftMenuInActive\"><a id=\"aID6415\" href=\"#\" OnMouseOver=\"link('_dir','component0',this)\" class=\"leftMenuLinkHeadInActive\">component</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6417\" class=\"leftMenuInActive\"><a id=\"aID6417\" href=\"#\" OnMouseOver=\"link('_dir','controller/controller0',this)\" class=\"leftMenuLinkInActive\">controller</a></div>\n");
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
