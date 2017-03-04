function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6492\" class=\"headerLeftMenuInActive\"><a id=\"aID6492\" href=\"#\" OnMouseOver=\"link('_dir','package_importer0',this)\" class=\"leftMenuLinkHeadInActive\">package_importer</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID6178\" class=\"leftMenuInActive\"><a id=\"aID6178\" href=\"#\" OnMouseOver=\"link('_class','Dialog0',this)\" class=\"leftMenuLinkInActive\">Dialog</a></div>\n");
document.write("<div id=\"divID1104\" class=\"leftMenuInActive\"><a id=\"aID1104\" href=\"#\" OnMouseOver=\"link('_class','PackageImporter22483',this)\" class=\"leftMenuLinkInActive\">PackageImporter</a></div>\n");
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
